using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Enemy : MonoBehaviour
{
    public GameObject Smoke;
    private NavMeshAgent owca;
    private Rigidbody rb;


    void Start ()
    {
        rb = GetComponent<Rigidbody>();
    }
	
	void Update ()
    {
        GetComponent<NavMeshAgent>().SetDestination(GameObject.FindGameObjectWithTag("Player").transform.position);
    }


    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            GetComponent<Collider>().enabled = false;

            GetComponent<Collider>().enabled = true;
        }
        if (collision.gameObject.tag == "Bullet")
        {
            Instantiate(Smoke, rb.position, rb.rotation);
            Destroy(collision.gameObject);
        }
    }
}
