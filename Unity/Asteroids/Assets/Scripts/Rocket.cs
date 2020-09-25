using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rocket : MonoBehaviour
{
    
    private GameObject Target;
    public float speed = 50;

    void Start()
    {
        Target = GameObject.FindGameObjectWithTag("Player");
    }

    void FixedUpdate()
    {
        float step = speed * Time.deltaTime;
        transform.position = Vector3.MoveTowards(transform.position, Target.transform.position, step);
    }

    void OnCollisionEnter(Collision collision)
    {

        Destroy(gameObject);
    }
    void Hunt()
    {
        float step = speed * Time.deltaTime;
        transform.position = Vector3.MoveTowards(transform.position, Target.transform.position, step);
    }

}