
const rotor = [
    'vñrn8lm5bdpa97ch1tzojgq6sx2f4yi3u0 wek',
    'apdzs 29cy5f10843ñq6v7jbheilxnukgmtorw',
    '3faclqr0o nx52kuñ4i76mhbezvpygd19j8stw',
    'pbjrdw59c30l1g2o8z 4shkufv6qñ7xyameint',
];

function change( el ) {
    el.value = el.value.toUpperCase();
}

function del() {
    document.querySelector("textarea").value = "";
}

function add( item ) {
    document.querySelector("textarea").value += item;
}

function bck() {
    document.querySelector("textarea").value = 
    document.querySelector("textarea").value.slice(0,-1);
}

function calculateRotation( length ){
	const rot = [0,0,0,0]; for( let i in rot ){ 
		let index = length; let p=i;
		while(p--) index /= rotor[i].length; 
				   index %= rotor[i].length;	
				   rot[i] = Math.floor(index);
	}	return rot;
}

function normalize( idx, A, B ){ 
	const acum = idx + A - B;
	if( acum >= rotor[0].length ) 
		return acum - rotor[0].length;
	else if( acum < 0  )
		return acum + rotor[0].length;
	else 
		return acum
}

function enc() {

    change( document.querySelector("textarea") );

    const encoded = document.querySelector("textarea")
                   .value.split('').map((x,i)=>{
		const rot = calculateRotation( i );
		[0,1,2,3,3,2,1,0].reduce((a,b)=>{ 
			
			if( a == b ) {
				let rt  = rotor[a].split('').reverse().join('');
				let idx = rt.toUpperCase().search(x);
					  x = rotor[a][idx].toUpperCase();
			} else {
				let idx = rotor[b].toUpperCase().search(x);
					idx = normalize( idx, rot[a], rot[b] );
					  x = rotor[a][idx].toUpperCase();
			}

			return b;
		}); return x;
	}).join('');

    document.querySelector("textarea").value = encoded;

}