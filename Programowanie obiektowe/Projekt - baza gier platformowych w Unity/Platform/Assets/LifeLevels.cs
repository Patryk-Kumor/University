using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeLevels : MonoBehaviour
{

    float x;
    float y;
    float dx;
    float dy;

    public int energy = 3;

    public GameObject Serce1;
    public GameObject Serce2;
    public GameObject Serce3;

    public PlayerMovement Cat;

    // Use this for initialization
    void Start()
    {
        Serce1 = GameObject.Find("Serce1");
        Serce2 = GameObject.Find("Serce2");
        Serce3 = GameObject.Find("Serce3");

        dx = transform.position.x - Camera.main.gameObject.transform.position.x;
        dy = transform.position.y - Camera.main.gameObject.transform.position.y;
    }

    // Update is called once per frame
    void Update()
    {
        Position();
        Energy();
    }

    void Position()
    {
        x = Camera.main.gameObject.transform.position.x + dx;
        y = Camera.main.gameObject.transform.position.y + dy;

        transform.position = new Vector3(x, y, transform.position.z);
    }

    void Energy()
    {
        if (energy == 3)
        {
            Serce3.GetComponent<Renderer>().enabled = true;
        }
        else
        {
            Serce3.GetComponent<Renderer>().enabled = false;
        }
        if (energy >= 2)
        {
            Serce2.GetComponent<Renderer>().enabled = true;
        }
        else
        {
            Serce2.GetComponent<Renderer>().enabled = false;
        }
        if (energy >= 1)
        {
            Serce1.GetComponent<Renderer>().enabled = true;
        }
        else
        {
            Serce1.GetComponent<Renderer>().enabled = false;
        }
        if (energy <= 0)
        {
            GameController.Reset();
        }
    }

    public void EnergyChange(int value)
    {

        if ((value == 1) && (energy == 3))
        {
            energy = 3;
        }
        else
        {
            energy = energy + value;
        }
    }

}
