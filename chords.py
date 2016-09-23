def transpose(n, chord):
    return map(lambda note: note + n, chord)

circle_of_fifths = [
    # G-flat, D-flat, A-flat
    6, 1, 8,
    # E-flat, B-flat, F, C
    3, 10, 5, 0,
    # G, D, A, E, B
    7, 2, 9, 4, 11
]

def get_chord(modifiers):
    # modifiers bit assignments
    # bit 2 is the first string, the minor string
    # bits 1 and 0 are the next two strings for adding stuff
    #   to the major or minor triad
    return [
        (0, 4, 7),        # major triad (these first two should never happen)
        (0, 4, 7, 10),    # major triad dominant 7th
        (0, 3, 7),        # minor triad
        (0, 3, 7, 10),    # minor with dominant 7th

        (0, 4, 7),        # major triad
        (0, 4, 7, 10),    # dominant 7th
        (0, 4, 7),        # major triad
        (0, 4, 7, 10),    # dominant 7th
    ][modifiers]

def pick_seven(offset, chord):
    chord = (
        transpose(offset - 24, chord) +
        transpose(offset - 12, chord) +
        transpose(offset, chord) +
        transpose(offset + 12, chord) +
        transpose(offset + 24, chord)
    )
    # Find the note closest to zero
    # If two are equally close, select the lower
    # Use this note as the middle of the seven strings
    dists = {}
    for i in range(len(chord)):
        key = abs(chord[i])
        if key not in dists:
            dists[key] = []
        dists[abs(chord[i])].append(i)
    for i in range(5):
        if i in dists and len(dists[i]) > 0:
            break
    assert i < 5
    middle_string = dists[i][0]
    return chord[middle_string-3:middle_string+4]

# Put the middle string as close as possible to middle C.
# Build a lookup table for sets of string pitch assignments.
lst = []
for modifiers in range(8):
    for i in circle_of_fifths:
        lst += transpose(60, pick_seven(i, get_chord(modifiers)))

outf = open("teensy/chords.cpp", "w")
outf.write("""unsigned char chord_table[] = {
""")
while True:
    if not lst:
        break
    n = 20
    sublist, lst = lst[:n], lst[n:]
    outf.write("  " + ",".join(map(str, sublist)) + (lst and "," or "") + "\n")
outf.write("""};
""")
outf.close()
