using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour
{

    private Rigidbody rb;
    public GameObject Fire;
    private float speed = 50;
    public float LifeTime = 10;

    void Start()
    {
        rb = GetComponent<Rigidbody>() as Rigidbody;
        Vector3 FORWARD = rb.transform.TransformDirection(Vector3.forward);
        rb.AddRelativeForce(0, 0, speed);
        rb.velocity = FORWARD * speed;
        Destroy(gameObject, LifeTime);
    }

    void OnCollisionEnter(Collision collision)
    {
        Instantiate(Fire, new Vector3(rb.transform.position.x, rb.transform.position.y, 0), rb.transform.rotation);
        Destroy(gameObject);
    }
}
