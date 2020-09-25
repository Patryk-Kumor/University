using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TreasureMoving : Treasure
{
    public Rigidbody2D Rigidbody;

    public float Speed = 50;

    public Transform[] Points;

    public Transform CurrentPoint;

    public int PointSelector;

    void Start()
    {
        Rigidbody = GetComponent<Rigidbody2D>() as Rigidbody2D;

        CurrentPoint = Points[PointSelector];
    }

    void Update()
    {
        new Vector2(0, 0);

        if (Rigidbody.transform.position.x - CurrentPoint.transform.position.x >= 0)
        {
            transform.right = Vector2.left;
        }
        else
        {
            transform.right = Vector2.right;
        }


        Rigidbody.transform.position = Vector3.MoveTowards(Rigidbody.transform.position,
                                                           CurrentPoint.position,
                                                           Time.deltaTime * Speed / 10);

        if (Rigidbody.transform.position == CurrentPoint.position)
        {
            PointSelector++;

            if (PointSelector >= Points.Length)
            {
                PointSelector = 0;
            }

            CurrentPoint = Points[PointSelector];
        }
    }
}
