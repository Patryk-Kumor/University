#pragma strict

var wings:Transform;
var freq:float = 12;
private var upSize:float = 1;
private var downSize:float = -0.5;

function Update () {
	var range:float = upSize-downSize;	
	var currSize:float = Mathf.PingPong(Time.time*freq, 1 )*range +downSize;	
	wings.localScale.z = currSize;
}