using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour 
{
	private Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

	public void OnCollisionEnter(Collision collision)
	{
		if (collision.gameObject.tag == "Ball")
		{
			Destroy(gameObject);
		}
	}
}
