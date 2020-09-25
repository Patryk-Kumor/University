using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rock : MonoBehaviour
{
    
    private GameObject Target;
    private Rigidbody rb;
    private float speed = 2;
   // public Texts Teksty;
    public GameObject MiniRock;

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
            //((PlayerMovement)Target).change();
            rb.isKinematic = true;
            gameObject.SetActive(false);
            Instantiate(MiniRock, new Vector3(rb.transform.position.x + 2f * rb.transform.right.x, rb.transform.position.y + 2f * rb.transform.right.y, 0), rb.transform.rotation);
            Instantiate(MiniRock, new Vector3(rb.transform.position.x + 4f * rb.transform.right.x, rb.transform.position.y + 4f * rb.transform.right.y, 0), rb.transform.rotation);
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
        rb.velocity = FORWARD* speed;
    }
    void Hunt()
    {
        float step = speed * Time.deltaTime;
        transform.position = Vector3.MoveTowards(transform.position, Target.transform.position, step);
    }
    void check(int range)
    {
        float x = rb.transform.position.x;
        float y = rb.transform.position.y;

        if ((x > range) || (x < -range))
        {
            transform.position = new Vector3(-rb.transform.position.x, rb.transform.position.y, 0);
        }
        if ((y > range) || (y < -range))
        {
            transform.position = new Vector3(rb.transform.position.x, -rb.transform.position.y, 0);
        }
    }

    
}
