// <!-- 1350685073
// This script is (C) Copyright 2004 Jim Tucek
// Leave these comments alone!  For more info, visit
// www.jracademy.com/~jtucek/email/ 

function bend(algebra,sponge,seat) {
algebra += ' ';
var assistant = algebra.length;
var bromide = 0;
var horse = '';
for(var song = 0; song < assistant; song++) {
bromide = 0;
while(algebra.charCodeAt(song) != 32) {
bromide = bromide * 10;
bromide = bromide + algebra.charCodeAt(song)-48;
song++;
}
horse += String.fromCharCode(leap(bromide,sponge,seat));
}
parent.location = 'm'+'a'+'i'+'l'+'t'+'o'+':'+horse;
}

function build(crust,thing,day) {
crust += ' ';
var age = crust.length;
var equipment = 0;
for(var hope = 0; hope < age; hope++) {
equipment = 0;
while(crust.charCodeAt(hope) != 32) {
equipment = equipment * 10;
equipment = equipment + crust.charCodeAt(hope)-48;
hope++;
}
//document.write('&');
//document.write('#');
//document.write(leap(equipment,thing,day));
document.write(String.fromCharCode(leap(equipment,thing,day)));
}
}

function leap(history,information,insect) {
if (insect % 2 == 0) {
side = 1;
for(var mortality = 1; mortality <= insect/2; mortality++) {
mission = (history*history) % information;
side = (mission*side) % information;
}
} else {
side = history;
for(var reason = 1; reason <= insect/2; reason++) {
mission = (history*history) % information;
side = (mission*side) % information;
}
}
return side;
}
