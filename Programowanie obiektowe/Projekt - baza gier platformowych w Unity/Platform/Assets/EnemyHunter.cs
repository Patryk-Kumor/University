using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyHunter : Enemy
{
    public bool IsRight = true;

    public float Speed = 20;

    public float JumpForce = 100;

    private GameObject Target;

    public Transform CurrentPoint;


    private bool GroundedFront;

    public Transform GroundCheckFront;

    private bool GroundedBack;

    public Transform GroundCheckBack;

    public float GroundCheckRadius;

    public LayerMask WhatIsPlatform;

    void Start()
    {
        Rigidbody = GetComponent<Rigidbody2D>() as Rigidbody2D;
        Target = GameObject.FindGameObjectWithTag("Player");

    }

    void Update()
    {
        GroundedFront = Physics2D.OverlapCircle(GroundCheckFront.position, GroundCheckRadius, WhatIsPlatform);
        GroundedBack = Physics2D.OverlapCircle(GroundCheckBack.position, GroundCheckRadius, WhatIsPlatform);

        new Vector2(0,0);

        if (Rigidbody.transform.position.x - Target.transform.position.x >= 0)
        {
            transform.right = Vector2.left;
        }
        else
        {
            transform.right = Vector2.right;
        }


        Rigidbody.transform.position = Vector3.MoveTowards(Rigidbody.transform.position,
                                                           Target.transform.position,
                                                           Time.deltaTime * Speed / 10);
        if ((GroundedBack)&&(!GroundedFront))
        {
            Rigidbody.AddForce(new Vector2(0, JumpForce));
        }

    }
}