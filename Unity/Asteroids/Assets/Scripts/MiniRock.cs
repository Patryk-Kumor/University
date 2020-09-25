using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiniRock : MonoBehaviour
{

    private GameObject Target;
    private Rigidbody rb;
    private float speed = 5;


    void Start()
    {
        rb = GetComponent<Rigidbody>();
        Target = GameObject.Find("SpaceshipFighter");
        Throw();
    }

    void FixedUpdate()
    {
        Throw();
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Bullet")
        {
            Target.GetComponent<PlayerMovement>().change();
            rb.isKinematic = true;
            gameObject.SetActive(false);

            Destroy(gameObject);
        }
        if (collision.gameObject.tag == "Enemy")
        {
            Vector3 dir = collision.contacts[0].point - transform.position;
            dir = -dir.normalized;
            GetComponent<Rigidbody>().AddForce(dir * speed);
        }
    }

    void Throw()
    {
        Vector3 FORWARD = rb.transform.TransformDirection(Vector3.forward);
        rb.AddRelativeForce(0, 0, speed);
        rb.velocity = FORWARD * speed;
    }

}
