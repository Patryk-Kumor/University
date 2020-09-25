using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public int Health = 3;

    public Rigidbody2D Rigidbody;

    public PlayerMovement Cat;

    public LifeLevels LifeLevel;


    void Start()
    {
        Rigidbody = GetComponent<Rigidbody2D>() as Rigidbody2D;
        Cat = FindObjectOfType<PlayerMovement>();
        LifeLevel = FindObjectOfType<LifeLevels>();
    }


    public void OnCollisionEnter2D(Collision2D collision)
    {

            Bullet bullet = collision.collider.GetComponent<Bullet>() as Bullet;

            if (bullet != null)
            {
                Health--;

                if (Health <= 0)
                {
                    Destroy(gameObject);
                }
            }
        

        if (collision.gameObject.tag == "Player")
        {
            LifeLevel.EnergyChange(-1);
            Cat.EnemyCollision();
        }
    }

}