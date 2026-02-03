#pragma once
#define CHARSET MEMSTR("012 QWE ASD ZXC 345 RTY FGH VBN 6789UIO JKL MP@<")

namespace enigma { namespace keyboard { GENERATOR( task ){
public: // Variable

  ptr_t<uint> data = ptr_t<uint>( 4, 0x00 );
  char id = 0; event_t<char> onKey;

public:

  void click_checker() const noexcept { 
    auto raw = encoder::bin::atob( data[id] );
    for( char x=raw.size(); x-->0; ){ 
    if ( raw[x] == 0 ) { continue; }
         onKey.emit( CHARSET[x*4+id] );
    }
  }

  coEmit() {
  coBegin

    while( true ){ while( id-->0 ){ coNext;

      digitalWrite( 4, HIGH ); digitalWrite( 5, HIGH );

      digitalWrite( 2, HIGH );
      shiftOut    ( 3, 13, MSBFIRST, 0x01 << id );
      digitalWrite( 2, LOW  );

      data[id]  = shiftIn( 6, 4, LSBFIRST );
      data[id]<<= 8;
      data[id] |= shiftIn( 6, 4, LSBFIRST );

      click_checker();

      digitalWrite( 4, LOW ); digitalWrite( 5, LOW );

    } id=4; coDelay(50); }

  coFinish }

};}}