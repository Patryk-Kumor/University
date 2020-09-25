#pragma strict
////
////	More Assets and Support in
////	http://assets.theweb3d.com 
////

var displacement:Vector3 = Vector3(5,2,5);
var desplVel:float = 1;


private var pos0:Vector3;

private var iniRndX:float;
private var iniRndY:float;
private var iniRndZ:float;

private var audioOn:boolean=false;

private var audioSourceMax:int = 4;
private var audioSourceCurr:int = 0;

function Start () {
	iniRndX = Random.Range(Random.Range(0,200), 500);
	iniRndY = Random.Range(Random.Range(0,200), 500);
	iniRndZ = Random.Range(Random.Range(0,200), 500);
	
	desplVel *= Random.Range(0.5, 2);
	
	pos0 = transform.localPosition;
	transform.localEulerAngles.y = Random.Range(1,360);
}

function Update() {
	
	//// Delete this Lines if you haven't an Audio Source attached to the GameObject
	if (!audioOn){
		if (Random.value < 0.01) {
			if(CheckAudioSourcesMax()) {
				GetComponent.<AudioSource>().Play();
				audioOn= true;
			} else {
				GetComponent.<AudioSource>().enabled = false;
				audioOn = true;
			}
		}
	}	
	////
}

function FixedUpdate () {
	UpdateDespl();
}

function UpdateDespl() {

	var x:float = (Mathf.PerlinNoise(Time.time*desplVel +iniRndX, iniRndX) -0.46525) *displacement.x;
	var y:float = (Mathf.PerlinNoise(iniRndY, iniRndY+ Time.time*desplVel) -0.46525) *displacement.y;
	var z:float = (Mathf.PerlinNoise(iniRndZ, iniRndZ+ Time.time*desplVel) -0.46525) *displacement.z;
	
	
	var despl:Vector3 = Vector3(x,y,z);
	var rot:Quaternion = Quaternion.LookRotation(despl, Vector3.up);
	rot.eulerAngles.x = 270;
	rot.eulerAngles.z = 0;
	rot.eulerAngles.y += 90;
	
	GetComponent.<Rigidbody>().AddForce(despl, ForceMode.Force);
	transform.rotation = Quaternion.Lerp(transform.rotation, rot, 0.09);
	 
	if ((transform.localPosition-pos0).sqrMagnitude>displacement.sqrMagnitude) {
		GetComponent.<Rigidbody>().AddForce((pos0 -transform.localPosition)*2, ForceMode.Force);
	}	
}

function CheckAudioSourcesMax():boolean {
	var maxNum:int = 0;
	var flyScripts:FlyBehav[] = FindObjectsOfType(FlyBehav);
	for(var flyScript:FlyBehav in flyScripts) {
		maxNum = Mathf.Max( flyScript.IncreaseAudioSourcesCurr(), maxNum);
	}
	if(maxNum<=audioSourceMax)	return true;
	else return false;
}

function IncreaseAudioSourcesCurr():int {
	audioSourceCurr ++;
	return audioSourceCurr;
}