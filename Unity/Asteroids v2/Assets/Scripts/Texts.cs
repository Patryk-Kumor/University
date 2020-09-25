using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Texts : MonoBehaviour
{
    public Text Lifes;

    public Text Points;

    public Text Coordinates;

    public Text Treasure;

    public int points = 0;

    public int lifes = 3;


    
    void Start ()
    {
        Lifes.text = "Lifes : " + lifes;
        Points.text = "Points : " + points;
        Coordinates.text = "Coordinates: <" + 0 + "," + 0 + ">";

    }

    private void FixedUpdate()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }

    }
    public int get_life()
    {
        return lifes;
    }
    public void gameover()
    {
        SceneManager.LoadScene(1);
    }
    public void LifeChange(int change)
    {
        lifes += change;
        Lifes.text = "Lifes : " + lifes;
    }
    public void LifeEnd()
    {
        lifes = 0;
        Lifes.text = "Lifes : " + lifes + ". You have lost!";
    }
    public void PointsChange(int change)
    {
        points += change;
        Points.text = "Points : " + points;
    }
    public void CoordinatesChange(float x, float y)
    {
        Coordinates.text = "Coordinates: <" + Mathf.Round(x) + "," + Mathf.Round(y) + ">";
    }
    public void CoordinatesTChange(float x, float y)
    {
        Treasure.text = "Next Treasure at: <" + Mathf.Round(x) + "," + Mathf.Round(y) + ">";
    }
    public void CoordinatesTEnd()
    {
        Treasure.text = "You have found all treasures!";
    }

}
