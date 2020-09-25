using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemySpider : MonoBehaviour
{
    public GameObject Smoke;
    private NavMeshAgent owca;
    private Rigidbody rb;

 
    private float playerDistance;

    void Start()
    {

        rb = GetComponent<Rigidbody>();
    }

    void Update()
    {
        if (GameObject.FindGameObjectWithTag("Player"))
        {
            GameObject player = GameObject.FindGameObjectWithTag("Player");
            playerDistance = Vector3.Distance(player.transform.position, transform.position);
            if (playerDistance >= 10f)
            {
                //GetComponent<Animation>().Play("Idle");
            }
            else
            {
                //GetComponent<Animation>().Play("walk");
                GetComponent<NavMeshAgent>().SetDestination(GameObject.FindGameObjectWithTag("Player").transform.position);
            }
        }

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
