using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Teksty : MonoBehaviour
{
    public Text Points;
    public Text Level;
    public Text Bonus;

    private int GamePoints;
    private int GameLevel;

    public GameObject Serce1;
    public GameObject Serce2;
    public GameObject Serce3;

    public GameObject Prefab;
    public Transform StartGame;

    public int lifes = 3;

    private float timer = 0;
    private float wait_time = 2f;
    private bool timerReady = false;

    private float timer2 = 0;
    private float wait_time2 = 2f;
    private bool timerReady2 = false;


    void Start ()
    {
        GamePoints = 0;
        GameLevel = 1;
        Points.text = "Points: 0";
        int SceneIndex = SceneManager.GetActiveScene().buildIndex;
        Level.text = "Level: " + SceneIndex;

        Bonus.text = " ";
    }

    void FixedUpdate()
    {
        if (timerReady)
        {
            timer += Time.deltaTime;
            if (timer > wait_time)
            {
                Instantiate(Prefab, StartGame.transform.position, StartGame.transform.rotation);
                timer = 0f;
                timerReady = false;
            }
        }
        if (timerReady2)
        {
            timer2 += Time.deltaTime;
            if (timer2 > wait_time2)
            {
                timer2 = 0f;
                timerReady2 = false;
                int nextSceneIndex = SceneManager.GetActiveScene().buildIndex + 1;
                if (nextSceneIndex == 3)
                {
                    SceneManager.LoadScene(0);
                }
                else
                {
                    SceneManager.LoadScene(nextSceneIndex);
                }
            

            }
        }
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene(0);
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);

        }
    }

    public void PointsChange(int change)
    {
        GamePoints += change;
        Points.text = "Points: " + GamePoints;
    }

    public void LifesChange(int change)
    {
        if (change < 0)
        {
            GetComponent<AudioSource>().Play();
            timerReady = true;
        }
        //Instantiate(Prefab, StartGame.transform.position, StartGame.transform.rotation);

        lifes += change;
        if (lifes >= 3) { lifes = 3; }
        if (lifes == 3)
        {
            Serce3.active = true;
        }
        else
        {
            Serce3.active = false;
        }
        if (lifes >= 2)
        {
            Serce2.active = true;
        }
        else
        {
            Serce2.active = false;
        }
        if (lifes >= 1)
        {
            Serce1.active = true;
        }
        else
        {
            Serce1.active = false;
        }
        if (lifes <= 0)
        {
            RestartLevel();
        }
    }

    public void RestartLevel()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
    public void NextLevel()
    {
        timerReady2 = true;
    }
}
