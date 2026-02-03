#define ROTOR0 string_t("7RE3 A8B@Z2UJNTY6XQ4P9OFDKCW05VGHMLI1S")
#define ROTOR1 string_t("9WL8NFOQP1RC3GDJ IAMZ6UKB40Y@HTSXV72E5")
#define ROTOR2 string_t("QUM@OLTZ1SKYXGV469 PNRWA72CDB0JI5HE8F3")

#define ROTORA string_t("LGR@1IMHNDQ6U4C9EXFPSAZO7BK 052YWT3JV8")
#define ROTORB string_t("8VJ3TWY250 KB7OZASPFXE9C4U6QDNHMI1@RGL")

inline uchar get_index( string_t data, char input, uchar rotA, uchar rotB ){
       uchar  idx = data.find( input )[0];
       char   acc = idx + rotA - rotB;
       return acc < 0? acc+38: acc%38;
}

string_t encrypt( string_t msg, ptr_t<uchar> rot ){ 
	
	queue_t<char> out; for( auto &idxx: msg ){

		if( ROTOR0.find( idxx ).null() ){ return nullptr; }

		/*-- ROTOR ROTATION LOGIC HERE --*/
		if( rot[1]==0 ){ rot[2] = (rot[2]+1)%38; }
		if( rot[0]==0 ){ rot[1] = (rot[1]+1)%38; }
		/*------------*/ rot[0] = (rot[0]+1)%38;

		char idx0 = ROTOR0[ get_index( ROTOR1, idxx, rot[0], rot[1] ) ];
		char idx1 = ROTOR1[ get_index( ROTOR2, idx0, rot[1], rot[2] ) ];
		char idx2 = ROTOR2[ get_index( ROTORA, idx1, rot[2], 0      ) ];
		
		char idx3 = ROTORB[ get_index( ROTOR2, idx2, 0     , rot[2] ) ];
		char idx4 = ROTOR2[ get_index( ROTOR1, idx3, rot[2], rot[1] ) ];
		char idx5 = ROTOR1[ get_index( ROTOR0, idx4, rot[1], rot[0] ) ];

    out.push( idx5 ); } out.push( '\0' ); return out.data().get();

}