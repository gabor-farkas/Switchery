let src = `
#include "NumpadMirror.h"

NumpadMirror::NumpadMirror(Board * board) {
    this->board = board;
}

void NumpadMirror::loop() {
    short charCode = board->getButtons()->read();
    if (charCode != -1) {
        if (charCode >> 4 == NL) {
            Serial.printf("%04x", charCode);
        }
    }
}
`;

src = src.replace(/#include.*/g, '');
src = src.replace(/(\w+)\:\:\1/g, '$1 = function');
src = src.replace(/(\w+)\:\:(\w+)/g, '$1.prototype.$2 = function');
src = src.replace(/function\(([^\s\)]+\s+)+(\w+)\)/g, 'function($2)');
src = src.replace(/->/g, '.');
src = src.replace(/void/g, '');
src = src.replace(/short\s/g, 'let ');

console.log(src);
console.log(eval(src));