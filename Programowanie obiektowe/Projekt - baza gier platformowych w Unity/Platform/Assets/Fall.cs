using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Fall : MonoBehaviour
{

    public PlayerMovement Cat;

    public LifeLevels LifeLevel;


    private void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.tag == "Player")
        {
            LifeLevel.EnergyChange(-1);
            Cat.EnemyCollision();
        }
    }
}
