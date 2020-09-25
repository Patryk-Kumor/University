using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{

    private Rigidbody2D Rigidbody;

    public float Speed = 10;

    public float LifeTime = 5;

    void Start()
    {
        Rigidbody = GetComponent<Rigidbody2D>() as Rigidbody2D;
     
        Rigidbody.velocity = new Vector2(Speed*transform.right.x, 0); 

        Destroy(gameObject, LifeTime); 
    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        Destroy(gameObject);
    }
    
}
