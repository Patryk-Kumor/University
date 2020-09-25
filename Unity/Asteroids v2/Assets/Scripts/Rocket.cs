using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rocket : MonoBehaviour
{
    
    private GameObject Target;
    public GameObject Fire;
    public float speed = 50;
    private Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        Target = GameObject.FindGameObjectWithTag("Player");
    }

    void FixedUpdate()
    {
        float step = speed * Time.deltaTime;
        transform.position = Vector3.MoveTowards(transform.position, Target.transform.position, step);
    }

    void OnCollisionEnter(Collision collision)
    {
        Instantiate(Fire, new Vector3(rb.transform.position.x, rb.transform.position.y, 0), rb.transform.rotation);
        Destroy(gameObject);
    }
    void Hunt()
    {
        float step = speed * Time.deltaTime;
        transform.position = Vector3.MoveTowards(transform.position, Target.transform.position, step);
    }

}