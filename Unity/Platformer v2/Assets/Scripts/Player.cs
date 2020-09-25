using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class Player : MonoBehaviour
{

    public GameObject Smoke;
    public GameObject Bullet;
    public Transform StartPoint;
    private GameObject StartGame;

    public GameObject PS;

    private GameObject Canvas;
    public Teksty TXT;

    private float timer;
    void Start ()
    {
       
        GetComponent<Animation>()["Ithcing"].layer = 1;
        GetComponent<Animation>()["Ithcing"].wrapMode = WrapMode.Once;
        GetComponent<Animation>()["Meow"].layer = 1;
        GetComponent<Animation>()["Meow"].wrapMode = WrapMode.Once;

        Canvas = GameObject.FindGameObjectWithTag("GameController");
        StartGame = GameObject.FindGameObjectWithTag("Start");

    }
	

	void Update ()
    {
        timer += Time.deltaTime;
        if (Input.GetKey(KeyCode.C))
        {
            GetComponent<Animation>().Play("Ithcing");
        }
        if (Input.GetKey(KeyCode.M))
        {
            GetComponent<AudioSource>().Play();
            GetComponent<Animation>().Play("Meow");
        }
        if (Input.GetButton("Fire1"))
        {
            if (timer > 0.5)
            {
                Instantiate(Bullet, StartPoint.position, StartPoint.rotation);
                timer = 0;
            }
            
        }
    }

    private void OnTriggerEnter(Collider hit)
    {
        if (hit.gameObject.tag == "Coin")
        {
            print("ZNALEZIONO MONETĘ");
            Canvas.GetComponent<Teksty>().PointsChange(1);
            Instantiate(PS, hit.transform.position, hit.transform.rotation);
            Destroy(hit.gameObject);
        }
        if (hit.gameObject.tag == "Food")
        {
            print("JEDZENIE!");
            Canvas.GetComponent<Teksty>().LifesChange(1);
            Instantiate(PS, hit.transform.position, hit.transform.rotation);
            Destroy(hit.gameObject);
        }
    }

    void OnControllerColliderHit(ControllerColliderHit hit)
    {
        if (hit.gameObject.tag == "Cel")
        {
            print("ZNALEZIONO CEL");
            GetComponent<AudioSource>().Play();
            Canvas.GetComponent<Teksty>().NextLevel();
        }
        if (hit.gameObject.tag == "Coin")
        {
            print("ZNALEZIONO MONETĘ");
            Canvas.GetComponent<Teksty>().PointsChange(1);
            Instantiate(PS, hit.transform.position, hit.transform.rotation);
            Destroy(hit.gameObject);
        }
        if (hit.gameObject.tag == "Enemy")
        {
            Instantiate(Smoke, transform.position, transform.rotation);
            Instantiate(Smoke, hit.transform.position, hit.transform.rotation);
            Destroy(hit.gameObject);
            print("OBRAŻENIA!");
            Canvas.GetComponent<Teksty>().LifesChange(-1);
            Destroy(gameObject);
        }
        if (hit.gameObject.tag == "Food")
        {
            print("JEDZENIE!");
            Canvas.GetComponent<Teksty>().LifesChange(1);
            Instantiate(PS, hit.transform.position, hit.transform.rotation);
            Destroy(hit.gameObject);
        }
    }


}
