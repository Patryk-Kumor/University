using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rock : MonoBehaviour
{
    
    private GameObject Target;
    private Rigidbody rb;
    private float speed = 2;

    public GameObject Fire;
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
        if (collision.gameObject.tag == "Rocket")
        {
            Target.GetComponent<PlayerMovement>().change();
            Instantiate(Fire, new Vector3(rb.transform.position.x, rb.transform.position.y, 0), rb.transform.rotation);
            //((PlayerMovement)Target).change();
            rb.isKinematic = true;
            gameObject.SetActive(false);
            Instantiate(MiniRock, new Vector3(rb.transform.position.x, rb.transform.position.y, 0), rb.transform.rotation);
        //    Instantiate(MiniRock, new Vector3(rb.transform.position.x + 3f * rb.transform.right.x, rb.transform.position.y + 3f * rb.transform.right.y, 0), rb.transform.rotation);
            Instantiate(MiniRock, new Vector3(rb.transform.position.x + 6f * rb.transform.right.x, rb.transform.position.y + 6f * rb.transform.right.y, 0), rb.transform.rotation);
            Destroy(gameObject);
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
    
}
