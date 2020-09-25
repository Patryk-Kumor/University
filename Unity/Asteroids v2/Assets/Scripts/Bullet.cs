using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{

    private Rigidbody rb;
    private float speed = 200;
    public float LifeTime = 5;

    void Start()
    {
        rb = GetComponent<Rigidbody>() as Rigidbody;
        Vector3 FORWARD = rb.transform.TransformDirection(Vector3.forward);
        rb.AddRelativeForce(0,0,speed);
        rb.velocity = FORWARD*speed;
        Destroy(gameObject, LifeTime);
    }

    void OnCollisionEnter(Collision collision)
    {
        Destroy(gameObject);
    }
}