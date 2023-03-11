const molly = require('./module/Molly');
const UIkit = require('./module/UIkit');

window.state = new device.state({
	text: '', encoded: ''
});

const rotor = [
	'5ñe3qlku207icwfvzjra9p4dxgn8shobt6m1y ',
	'3qip8zrxh2u4waf5n0ñty6de19bolsck7vj mg',
	'lr1c2xnzfwqbi05shujy6dñt7mk984g3oapve ',
	'3syqj6olki59dh1r4vwb8ñ7 etcaxz2pnmu0gf',
]

function calculateRotation( length ){
	const rot = [0,0,0,0]; for( let i in rot ){ 
		let index = length; let p=i;
		while(p--) index /= rotor[i].length; 
		while(index>=rotor[i].length) index-= rotor[i].length;
		if( index < 0 ) index = 0; rot[i] = Math.floor( index );
	}	return rot;
}

function normalize( int,A,B ){ 
	const acum = int+A-B;
	if( acum >= rotor[0].length ) 
		return acum - rotor[0].length;
	else if( acum < 0  )
		return acum + rotor[0].length;
	else 
		return acum
}

window.state.observeField('text',(prev,act)=>{
	const encoded = act.split('').map((x,i)=>{
		const rot = calculateRotation(i);
		[0,1,2,3,4,2,1,0].reduce((a,b)=>{ 
			
			if( a == 3 && b == 4 ) {
				let rt  = rotor[a].split('').reverse().join('');
				let int = rt.toUpperCase().search(x);
					  x = rotor[a][int].toUpperCase();
				return a;
			} else {
				let int = rotor[b].toUpperCase().search(x);
					int = normalize( int, rot[a], rot[b] );
					  x = rotor[a][int].toUpperCase();
			}

			return b;
		}); return x;
	});
	window.state.set({ encoded: encoded.join('') });
});