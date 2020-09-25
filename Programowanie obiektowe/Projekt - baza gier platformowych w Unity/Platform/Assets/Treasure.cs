using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Treasure : MonoBehaviour
{
    public Score MyScore;

    public int Value = 1;

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.name == "Cat")
        {
            MyScore.ChangeScore(1);
            Destroy(gameObject);
        }
    }
}
