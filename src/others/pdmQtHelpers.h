//
// Created by Mike Yang on 2023/8/17.
//

#ifndef PDM_QT_PDMQTHELPERS_H
#define PDM_QT_PDMQTHELPERS_H


#include <qcolor.h>

namespace PDM::Helpers {
    namespace QtColor {

        static void copy_rgb(const QColor& from , QColor*to){
          to->setRed(from.red());
          to->setGreen(from.green());
          to->setBlue(from.blue());
        }
    }
}


#endif //PDM_QT_PDMQTHELPERS_H

/**
         * THE QT COLOR NAME LIST AND INDEX:
         *
         * Color list #0: aliceblue
            Color list #1: antiquewhite
            Color list #2: aqua
            Color list #3: aquamarine
            Color list #4: azure
            Color list #5: beige
            Color list #6: bisque
            Color list #7: black
            Color list #8: blanchedalmond
            Color list #9: blue
            Color list #10: blueviolet
            Color list #11: brown
            Color list #12: burlywood
            Color list #13: cadetblue
            Color list #14: chartreuse
            Color list #15: chocolate
            Color list #16: coral
            Color list #17: cornflowerblue
            Color list #18: cornsilk
            Color list #19: crimson
            Color list #20: cyan
            Color list #21: darkblue
            Color list #22: darkcyan
            Color list #23: darkgoldenrod
            Color list #24: darkgray
            Color list #25: darkgreen
            Color list #26: darkgrey
            Color list #27: darkkhaki
            Color list #28: darkmagenta
            Color list #29: darkolivegreen
            Color list #30: darkorange
            Color list #31: darkorchid
            Color list #32: darkred
            Color list #33: darksalmon
            Color list #34: darkseagreen
            Color list #35: darkslateblue
            Color list #36: darkslategray
            Color list #37: darkslategrey
            Color list #38: darkturquoise
            Color list #39: darkviolet
            Color list #40: deeppink
            Color list #41: deepskyblue
            Color list #42: dimgray
            Color list #43: dimgrey
            Color list #44: dodgerblue
            Color list #45: firebrick
            Color list #46: floralwhite
            Color list #47: forestgreen
            Color list #48: fuchsia
            Color list #49: gainsboro
            Color list #50: ghostwhite
            Color list #51: gold
            Color list #52: goldenrod
            Color list #53: gray
            Color list #54: green
            Color list #55: greenyellow
            Color list #56: grey
            Color list #57: honeydew
            Color list #58: hotpink
            Color list #59: indianred
            Color list #60: indigo
            Color list #61: ivory
            Color list #62: khaki
            Color list #63: lavender
            Color list #64: lavenderblush
            Color list #65: lawngreen
            Color list #66: lemonchiffon
            Color list #67: lightblue
            Color list #68: lightcoral
            Color list #69: lightcyan
            Color list #70: lightgoldenrodyellow
            Color list #71: lightgray
            Color list #72: lightgreen
            Color list #73: lightgrey
            Color list #74: lightpink
            Color list #75: lightsalmon
            Color list #76: lightseagreen
            Color list #77: lightskyblue
            Color list #78: lightslategray
            Color list #79: lightslategrey
            Color list #80: lightsteelblue
            Color list #81: lightyellow
            Color list #82: lime
            Color list #83: limegreen
            Color list #84: linen
            Color list #85: magenta
            Color list #86: maroon
            Color list #87: mediumaquamarine
            Color list #88: mediumblue
            Color list #89: mediumorchid
            Color list #90: mediumpurple
            Color list #91: mediumseagreen
            Color list #92: mediumslateblue
            Color list #93: mediumspringgreen
            Color list #94: mediumturquoise
            Color list #95: mediumvioletred
            Color list #96: midnightblue
            Color list #97: mintcream
            Color list #98: mistyrose
            Color list #99: moccasin
            Color list #100: navajowhite
            Color list #101: navy
            Color list #102: oldlace
            Color list #103: olive
            Color list #104: olivedrab
            Color list #105: orange
            Color list #106: orangered
            Color list #107: orchid
            Color list #108: palegoldenrod
            Color list #109: palegreen
            Color list #110: paleturquoise
            Color list #111: palevioletred
            Color list #112: papayawhip
            Color list #113: peachpuff
            Color list #114: peru
            Color list #115: pink
            Color list #116: plum
            Color list #117: powderblue
            Color list #118: purple
            Color list #119: red
            Color list #120: rosybrown
            Color list #121: royalblue
            Color list #122: saddlebrown
            Color list #123: salmon
            Color list #124: sandybrown
            Color list #125: seagreen
            Color list #126: seashell
            Color list #127: sienna
            Color list #128: silver
            Color list #129: skyblue
            Color list #130: slateblue
            Color list #131: slategray
            Color list #132: slategrey
            Color list #133: snow
            Color list #134: springgreen
            Color list #135: steelblue
            Color list #136: tan
            Color list #137: teal
            Color list #138: thistle
            Color list #139: tomato
            Color list #140: transparent
            Color list #141: turquoise
            Color list #142: violet
            Color list #143: wheat
            Color list #144: white
            Color list #145: whitesmoke
            Color list #146: yellow
            Color list #147: yellowgreen
         *
         * */