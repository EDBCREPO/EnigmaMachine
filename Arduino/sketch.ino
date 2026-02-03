#include <LiquidCrystal_I2C.h>

#include <nodepp.h>
#include <nodepp/event.h>
#include <nodepp/encoder.h>

const char OUT[] PROGMEM = { 13, 12, 11, 10, 8, 7, 5, 4, 3, 2 };
const char INP[] PROGMEM = { 9, 6 };

using namespace nodepp;

#include "memory.h"

#include "utils.h"
#include "rotor.h"
#include "board.h"
#include "screen.h"

namespace enigma { void main() {

  for( auto x: memory::get<char>( OUT, 10 ) ){ pinMode( x, OUTPUT ); }
  for( auto x: memory::get<char>( INP,  2 ) ){ pinMode( x, INPUT  ); }

  /* keyboard Task */
  auto t2 = keyboard::task(); process::add( t2 );

  /* Screen Task */
  auto t1 = screen::task(); process::add( t1 );

  /* rotor IO Task */
  auto t0 = rotor::task(); process::add( t0 );

  /* OnKeyboarClickEvent */
  t2.onKey.on([=]( char key ){ 
    if(key=='<'){ t1.clear(); return; }
    t1.append( t0.encode(key), key );
  });

}}

void onMain() { enigma::main(); }