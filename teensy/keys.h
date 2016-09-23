#ifndef KEYS_H_DEFINED
#define KEYS_H_DEFINED

#define KEYDOWN_HYSTERESIS 10

#ifndef max
#define max(x, y)  (((x) > (y)) ? (x) : (y))
#endif

// typedef unsigned char uint8_t;
// typedef unsigned long int uint32_t;

class BaseKey
{
public:
    uint32_t threshold;

    uint32_t successive_approximate(uint32_t lo, uint32_t hi) {
        if (hi < lo) return successive_approximate(hi, lo);
        if (hi - lo <= 1) return hi;
        uint32_t mid = (lo + hi) >> 1;
        if (!read_n(mid))
            return successive_approximate(lo, mid);
        else
            return successive_approximate(mid, hi);
    }

    virtual bool read_n(uint32_t n) = 0;

    /**
     * A numerical index of this key, used to identify it for keyboard scanning.
     */
    uint32_t id;
    /**
     * 1 if the key is pressed/touched, 0 otherwise.
     */
    uint32_t state;
    /**
     * This counter is used for hysteresis (debouncing).
     */
    uint32_t count;

    BaseKey(uint32_t _id) {
        id = _id;
        count = state = 0;
    }

    int fresh_calibrate(void) {
        threshold = 0;
        return calibrate();
    }

    int calibrate(void) {
        const int _max = 250;
        int previous = 0, n;
        for (n = 1; n < _max; n <<=1) {
            if (!read_n(n)) {
                threshold =
                    max(threshold, successive_approximate(previous, n) + 1);
                return threshold;
            }
            previous = n;
        }
        threshold = max(threshold, _max);   // out of luck, probably
        return threshold;
    }

    /**
     * Detect whether a key is being pressed or touched. This is a single
     * detection prior to any debouncing logic.
     */
    bool read(void) {
        return read_n(threshold);
    }

    /**
     * Checks to see if this key is being pressed/touched. Debounces using a
     * hysteresis state machine.
     */
    void check(void) {
        if (read()) {
            if (state) {
                count = 0;
            } else {
                if (count < KEYDOWN_HYSTERESIS) {
                    count++;
                    if (count == KEYDOWN_HYSTERESIS) {
                        state = 1;
                        count = 0;
                        keydown();
                    }
                }
            }
        } else {
            if (!state) {
                count = 0;
            } else {
                if (count < KEYDOWN_HYSTERESIS) {
                    count++;
                    if (count == KEYDOWN_HYSTERESIS) {
                        state = 0;
                        count = 0;
                        keyup();
                    }
                }
            }
        }
    }

    virtual void keydown(void) {}
    virtual void keyup(void) {}
};


class KeyGroup
{
protected:
    int8_t _previous_pressed = 0;
    int8_t num_keys = 0;
    int8_t _value;
    int8_t _any_pressed;
    BaseKey *keys[16];
    virtual int8_t raw_value(void) {
        int8_t i, y = 0, value = 0;
        for (i = 0; i < num_keys; i++)
            if (keys[i]->state) {
                value |= (1 << i);
                y = 1;
            }
        if (y) return value;
        else return -1;
    }

public:
    KeyGroup(int8_t default_value) {
        _value = default_value;
    }
    void scan(void) {
        int i = raw_value();
        if (i != -1) {
            _any_pressed = 1;
            _value = i;
        } else {
            _any_pressed = 0;
        }
    }
    void add(BaseKey *k) {
        keys[num_keys++] = k;
    }
    void update(void) {
        _previous_pressed = _any_pressed;
    }
    int8_t value(void) {
        return _value;
    }
    int8_t previous_pressed(void) {
        return _previous_pressed;
    }
    int8_t any_pressed(void) {
        return _any_pressed;
    }
};


class KeySelect : public KeyGroup
{
protected:
    int8_t raw_value(void) {
        int8_t i;
        for (i = 0; i < num_keys; i++)
            if (keys[i]->state)
                return i;
        return -1;
    }
public:
    KeySelect(int8_t default_value) : KeyGroup(default_value) { }
};

#endif   // KEYS_H_DEFINED
