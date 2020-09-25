using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThrowRock : MonoBehaviour
{
    float tempX;
    float tempY;

    private GameObject Target;
    private Rigidbody rb;
    private float speed = 5000;
    public GameObject Fire;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        Target = GameObject.Find("SpaceshipFighter");
        if (Random.Range(-1, 1) >= 0)
        {
            rb.AddForce(rb.transform.forward * speed, ForceMode.Impulse);
        }
        else
        {
            rb.AddForce(-rb.transform.forward * speed, ForceMode.Impulse);
        }
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


    }
}
