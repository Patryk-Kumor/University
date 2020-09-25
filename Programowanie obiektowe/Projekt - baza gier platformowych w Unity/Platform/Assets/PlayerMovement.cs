using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    private Rigidbody2D Rigidbody;

    public bool IsRight = true;

    public float Speed = 10;

    public float JumpForce = 1500;



    public Transform SpawnPoint;

    private bool Grounded;

    private bool GroundedBack;

    public Transform GroundCheck;

    public Transform GroundCheckBack;

    public float GroundCheckRadius;

    public LayerMask WhatIsPlatform;


    void Start()
    {
        Rigidbody = GetComponent<Rigidbody2D>() as Rigidbody2D;
    }



    void OnTriggerEnter2D(Collider2D other) 
    {
        if (other.gameObject.tag == "Platform") 
        {
             transform.parent = other.gameObject.transform;
        }
    }

    public void EnemyCollision()
    {
        transform.position = SpawnPoint.transform.position;
    }

    void FixedUpdate() 
    {
        Grounded = Physics2D.OverlapCircle(GroundCheck.position, GroundCheckRadius, WhatIsPlatform);
        GroundedBack = Physics2D.OverlapCircle(GroundCheckBack.position, GroundCheckRadius, WhatIsPlatform);

        if (Input.GetButton("Horizontal"))
        {
            Rigidbody.velocity = new Vector2(Input.GetAxis("Horizontal") * Speed, Rigidbody.velocity.y);

            if (Rigidbody.velocity != Vector2.zero)
            {
                if (Rigidbody.velocity.x < 0)
                {
                    IsRight = false;
                    transform.right = Vector2.left;
                }
                else
                {
                    transform.right = Vector2.right;
                    IsRight = true;
                }
            }
        }
    
        if (Input.GetKeyDown("down"))
        {
            Rigidbody.velocity = new Vector2(Rigidbody.velocity.x, Speed * -1);
        }

        if (Input.GetButton("Jump") && (Grounded||GroundedBack))
        {
            Rigidbody.AddForce(new Vector2(0, Input.GetAxis("Jump") * JumpForce));
        }
    }
}