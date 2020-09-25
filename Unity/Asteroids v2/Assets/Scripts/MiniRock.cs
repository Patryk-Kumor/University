using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiniRock : MonoBehaviour
{

    private GameObject Target;
    private Rigidbody rb;
    private float speed = 5;
    private float speed2 = 500;
    public GameObject Fire;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        Target = GameObject.Find("SpaceshipFighter");

    }

    void FixedUpdate()
    {
        Throw();
    }

    void OnCollisionEnter(Collision collision)
    {
        if ((collision.gameObject.tag == "Bullet") || (collision.gameObject.tag == "Rocket"))
        {
            Instantiate(Fire, new Vector3(rb.transform.position.x, rb.transform.position.y, 0), rb.transform.rotation);
            Target.GetComponent<PlayerMovement>().change();
            rb.isKinematic = true;
            gameObject.SetActive(false);

            Destroy(gameObject);
        }

    }

    void Throw()
    {
        Vector3 FORWARD = rb.transform.TransformDirection(Vector3.forward);
        rb.AddRelativeForce(Random.onUnitSphere * speed);
        rb.AddRelativeForce(0, 0, speed);
        rb.velocity = FORWARD * speed;
    }
}
