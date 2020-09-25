using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class PlayerMovement : MonoBehaviour
{
    private Rigidbody rb;
    public float speed = 25;

    public GameObject Bullet;
    public GameObject myBomb;
    public GameObject Meteor;
    public GameObject Rock;
    public GameObject MiniRock;
    public GameObject Fire;

    public GameObject Treasure;
    public GameObject Bomb;

    public Transform BulletSpawnPoint;
    public Transform BombSpawnPointL;
    public Transform BombSpawnPointR;

    bool L_R = true;

    private float waitTime = 5f; private float waitTime2 = 10f; private float waitTime_M = 15f;
    float timer; float timer2; float timer_b; float timer_m;

    public Texts Teksty;
    bool Is_found;
    private int lifes =3;

    void Start ()
    {
        rb = GetComponent<Rigidbody>();
        Is_found = false;
        float x1 = Random.Range(-250, 250);
        float y1 = Random.Range(-250, 250);
        Instantiate(Treasure, new Vector3(x1, y1, 0), rb.transform.rotation);
        Teksty.CoordinatesTChange(x1, y1);
        for (int i = 1; i <= 100; i++)
        {
           spawn_all(750);
           spawn_all_small(750);
        }
    }

    void FixedUpdate()
    {

     //   float ps = rb.velocity.magnitude;
    //    Fire.GetComponent<ParticleSystem>().Stop();

     //   var main2 = Fire.GetComponent<ParticleSystem>().main;

     //   main2.duration = ps*1000000;

       

//Fire.GetComponent<ParticleSystem>().Play();

        timer_b += Time.deltaTime;

        if (Is_found)
        {
            spawn_t();
            Is_found = false;
        }

        Teksty.CoordinatesChange(rb.transform.position.x, rb.transform.position.y);

        timer += Time.deltaTime;
        if (timer > waitTime)
        {
            spawn(100);
            spawn_mini(100);
            timer = 0f;
            if ((waitTime) > 1f)
            {
                waitTime -= 0.25f;
            }
            else
            {
                waitTime = 2f;
            }
        }
        timer2 += Time.deltaTime;
        if (timer2 > waitTime2)
        {
            spawn_bomb(100);

            timer2 = 0f;
            if ((waitTime2) > 1f)
            {
                waitTime2 -= 0.5f;
            }
            else
            {
                waitTime2 = 2.5f;
            }
        }
        timer_m += Time.deltaTime;
        if (timer_m > waitTime_M)
        {
            Instantiate(Meteor, new Vector3(rb.transform.position.x+75f, rb.transform.position.y+75f, 0), rb.rotation);
            timer_m = 0f;
        }

        var x = Input.GetAxis("Horizontal") * Time.deltaTime * 100.0f;
        transform.Rotate(0, x, 0);
        float acceleration = -Input.GetAxis("Vertical");
        rb.AddForce(transform.forward * acceleration * speed);

        if (Input.GetKey("space"))
        {
            rb.velocity = rb.velocity / 2;


        }
        if (Input.GetButton("Fire1"))
        {
            if (timer_b >= 0.2)
            {
                AudioSource audio = GetComponent<AudioSource>();
                audio.Play();
                audio.Play(44100);
                timer_b = 0f;
                Instantiate(Bullet, BulletSpawnPoint.position, BulletSpawnPoint.rotation);
            }
        }
        if (Input.GetButtonDown("Fire2"))
        {
            if (L_R)
            {
                L_R = false;
                Instantiate(myBomb, BombSpawnPointL.position, BombSpawnPointL.rotation);
            }
            else
            {
                L_R = true;
                Instantiate(myBomb, BombSpawnPointR.position, BombSpawnPointR.rotation);
            }
        }
    }

    void spawn(float range)
    {
        float x = rb.transform.position.x;
        float y = rb.transform.position.y;
        if (Random.Range(-1, 1) >= 0)
        { Instantiate(Rock, new Vector3(Random.Range(x - range, x + range), y + range, 0), rb.transform.rotation); }
        else
        { Instantiate(Rock, new Vector3(Random.Range(x - range, x + range), y - range, 0), rb.transform.rotation); }
    }
    void spawn_mini(float range)
    {
        float x = rb.transform.position.x;
        float y = rb.transform.position.y;
        if (Random.Range(-1, 1) >= 0)
        { Instantiate(MiniRock, new Vector3(Random.Range(x - range, x + range), y + range, 0), rb.transform.rotation); }
        else
        { Instantiate(MiniRock, new Vector3(Random.Range(x - range, x + range), y - range, 0), rb.transform.rotation); }
    }

    void spawn_all(float range)
    {
        float random = (Random.Range(-1, 1));
        if (random <= -0.5f) { Instantiate(Rock, new Vector3(Random.Range(100, range), Random.Range(-range, range), 0), rb.transform.rotation); }
        if (random <= 0) { Instantiate(Rock, new Vector3(Random.Range(-range, range), Random.Range(100, range), 0), rb.transform.rotation); }
        if (random <= 0.5f) { Instantiate(Rock, new Vector3(Random.Range(-range, -100), Random.Range(-range, range), 0), rb.transform.rotation); }
        if (random <= 1) { Instantiate(Rock, new Vector3(Random.Range(-range, range), Random.Range(-range, 100), 0), rb.transform.rotation); }
        
    }
    void spawn_all_small(float range)
    {
        float random = (Random.Range(-1, 1));
        if (random <= -0.5f) { Instantiate(MiniRock, new Vector3(Random.Range(100, range), Random.Range(-range, range), 0), rb.transform.rotation); }
        if (random <= 0) { Instantiate(MiniRock, new Vector3(Random.Range(-range, range), Random.Range(100, range), 0), rb.transform.rotation); }
        if (random <= 0.5f) { Instantiate(MiniRock, new Vector3(Random.Range(-range, -100), Random.Range(-range, range), 0), rb.transform.rotation); }
        if (random <= 1) { Instantiate(MiniRock, new Vector3(Random.Range(-range, range), Random.Range(-range, 100), 0), rb.transform.rotation); }

    }
    void spawn_bomb(float range)
    {
        float x = rb.transform.position.x;
        float y = rb.transform.position.y;
        if (Random.Range(-1, 1) >= 0)
        { Instantiate(Bomb, new Vector3(Random.Range(x - range, x + range), y + range, 0), rb.transform.rotation); }
        else
        { Instantiate(Bomb, new Vector3(Random.Range(x - range, x + range), y - range, 0), rb.transform.rotation); }
    }
    void spawn_t()
    {
        float x1 = Random.Range(-250, 250);
        float y1 = Random.Range(-250, 250);
        Instantiate(Treasure, new Vector3(x1, y1, 0), rb.transform.rotation);
        Teksty.CoordinatesTChange(x1, y1);
    }


    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Enemy")
        {
            Teksty.LifeChange(-1);
            lifes -= 1;
            rb.velocity = rb.velocity / 2;
            if (lifes == 0) { Destroy(gameObject); Teksty.LifeEnd(); Teksty.gameover(); }
            transform.position = new Vector3(0, 0, 0);

            rb.velocity = rb.velocity / 2;
        }
        if (collision.gameObject.tag == "Treasure")
        {
            Is_found = true;
            Teksty.PointsChange(10);
        }
    }


    public void change()
    {
        Teksty.PointsChange(1);
    }
}
