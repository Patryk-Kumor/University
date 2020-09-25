using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingPlatform : MonoBehaviour
{

    public GameObject Platform;

    public float Speed = 20;

    public Transform[] Points;

    public Transform CurrentPoint;

    public int PointSelector;

    void Start ()
    {
        CurrentPoint = Points[PointSelector];
    }


    void Update ()
    {
        Platform.transform.position = Vector3.MoveTowards(Platform.transform.position,
                                                          CurrentPoint.position,
                                                          Time.deltaTime*Speed/10);

        if  (Platform.transform.position == CurrentPoint.position)
        {
            PointSelector++;

            if (PointSelector>=Points.Length)
            {
                PointSelector = 0;
            }

            CurrentPoint = Points[PointSelector];
        }
    }
}
