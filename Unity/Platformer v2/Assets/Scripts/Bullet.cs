using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour {

    private Rigidbody rb;
    private float speed = 5;
    private float LifeTime = 5;

    public GameObject Fire;
    public GameObject BigFire;

    void Start ()
    {
        rb = GetComponent<Rigidbody>();
        Destroy(gameObject, LifeTime);
    }
	

	void FixedUpdate ()
    {
        rb.velocity = transform.TransformDirection(Vector3.forward * speed);
    }

    void OnCollisionEnter(Collision collision)
    {
        Instantiate(Fire, rb.position, rb.rotation);
        if (collision.gameObject.tag == "Bomb")
        {
            Instantiate(BigFire, rb.position, rb.rotation);
            Destroy(collision.gameObject);
        }
        if (collision.gameObject.tag == "Enemy")
        {

            Destroy(collision.gameObject);
        }
        Destroy(gameObject);
    }


}
