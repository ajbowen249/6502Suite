const charWidth = 5;
const charHeight = 8;

const spacingWidth = 1;
const spacingHeight = 1;

const charData = {
    '@': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 0, 1, 1, 1, ], [ 1, 0, 1, 1, 0, ], [ 1, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 1, ], ],
    'A': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 1, 1, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], ],
    'B': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 1, 1, 0, ], ],
    'C': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    'D': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 1, 1, 0, ], ],
    'E': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], ],
    'F': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], ],
    'G': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 1, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 1, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 1, ], ],
    'H': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 1, 1, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], ],
    'I': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 1, 1, 0, ], ],
    'J': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    'K': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 1, 0, ], [ 1, 0, 1, 0, 0, ], [ 1, 1, 0, 0, 0, ], [ 1, 0, 1, 0, 0, ], [ 1, 0, 0, 1, 0, ], [ 1, 0, 0, 0, 1, ], ],
    'L': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], ],
    'M': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 0, 1, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], ],
    'N': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 0, 0, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 0, 1, 1, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], ],
    'O': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    'P': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], ],
    'Q': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 0, 0, 1, 0, ], [ 0, 1, 1, 0, 1, ], ],
    'R': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 1, 0, 0, ], [ 1, 0, 0, 1, 0, ], [ 1, 0, 0, 0, 1, ], ],
    'S': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 0, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    'T': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], ],
    'U': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    'V': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], ],
    'W': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 1, 0, 1, 1, ], [ 1, 0, 0, 0, 1, ], ],
    'X': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], ],
    'Y': [ [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], ],
    'Z': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], ],
    '[': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 1, 1, 0, 0, 0, ], [ 1, 1, 0, 0, 0, ], [ 1, 1, 0, 0, 0, ], [ 1, 1, 0, 0, 0, ], [ 1, 1, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], ],
    '\\':[ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 0, ], ],
    ']': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 1, 1, ], [ 0, 0, 0, 1, 1, ], [ 0, 0, 0, 1, 1, ], [ 0, 0, 0, 1, 1, ], [ 0, 0, 0, 1, 1, ], [ 1, 1, 1, 1, 1, ], ],
    '^': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    '_': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], ],
    ' ': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    '!': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], ],
    '"': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 0, 1, 0, ], [ 0, 1, 0, 1, 0, ], [ 0, 1, 0, 1, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    '#': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 0, 1, 0, ], [ 0, 1, 0, 1, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 1, 0, 1, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 1, 0, 1, 0, ], [ 0, 1, 0, 1, 0, ], ],
    '$': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 1, 1, 1, ], [ 1, 0, 1, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 0, 0, 1, 0, 1, ], [ 1, 1, 1, 1, 0, ], [ 0, 0, 1, 0, 0, ], ],
    '%': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 0, 0, 0, ], [ 1, 1, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 0, 1, 1, ], [ 0, 0, 0, 1, 1, ], ],
    '&': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 1, 0, 0, ], [ 1, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 1, 0, 1, ], [ 1, 0, 0, 1, 0, ], [ 0, 1, 1, 0, 1, ], ],
    '\'':[ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    '(': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], ],
    ')': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], ],
    '*': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 1, 0, 1, 0, 1, ], [ 0, 1, 1, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 1, 0, 1, ], [ 0, 0, 1, 0, 0, ], ],
    '+': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    ',': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], ],
    '-': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    '.': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], ],
    '/': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    '0': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 1, 1, ], [ 1, 0, 1, 0, 1, ], [ 1, 1, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    '1': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 1, 1, 0, ], ],
    '2': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 1, 1, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], ],
    '3': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 1, 0, ], [ 0, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    '4': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 1, 0, ], [ 0, 1, 0, 1, 0, ], [ 1, 0, 0, 1, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 0, 1, 0, ], ],
    '5': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    '6': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 1, 1, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    '7': [ [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 0, 1, 0, 0, 0, ], ],
    '8': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 0, ], ],
    '9': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 1, 0, 0, 0, 1, ], [ 0, 1, 1, 1, 1, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 1, 1, 1, 0, 0, ], ],
    ':': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], ],
    ';': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], ],
    '<': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 1, 0, 0, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 1, 0, ], ],
    '=': [ [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 0, 0, ], [ 1, 1, 1, 1, 1, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 0, 0, 0, ], ],
    '>': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 1, 0, 0, 0, ], ],
    '?': [ [ 0, 0, 0, 0, 0, ], [ 0, 1, 1, 1, 0, ], [ 1, 0, 0, 0, 1, ], [ 0, 0, 0, 1, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 1, 0, 0, ], [ 0, 0, 0, 0, 0, ], [ 0, 0, 1, 0, 0, ], ],
};

function drawChar(canvas, char, x, y) {
    const charMap = charData[char];
    if (!charMap) {
        return false;
    }

    for(let i = 0; i < charHeight; i++) {
        for(let j = 0; j < charWidth; j++) {
            if ( charMap[i][j] === 1) {
                canvas.fillRect(x + j, y + i, 1, 1);
            }
        }
    }

    return true;
}

function drawScreen(nativeWidth, nativeHeight, scaleX, scaleY, lines, canvas) {
    canvas.setTransform(1, 0, 0, 1, 0, 0);
    canvas.scale(scaleX, scaleY);

    canvas.fillStyle = '#000000';
    canvas.fillRect(0, 0, nativeWidth, nativeHeight);
    canvas.fillStyle = '#00FF00';
    let y = 0;
    for(let i = 0; i < lines.length; i++) {
        let x = 0;
        const line = lines[i];
        for(let j = 0; j < line.length; j++) {
            if (drawChar(canvas, line.charAt(j), x, y)) {
                x += charWidth + spacingWidth;
            }
        }

        y += charHeight + spacingHeight;
    }
}
