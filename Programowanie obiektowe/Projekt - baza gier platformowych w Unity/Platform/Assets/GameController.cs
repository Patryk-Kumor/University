using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameController : MonoBehaviour
{
    private static GameController Instance;

    void Start()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
        }

        DontDestroyOnLoad(gameObject);
    }

    void Update()
    {
        if (Input.GetButton("Cancel"))
        {
            Application.Quit();
        }
    }

    public static void NextLevel()
    {
        int y = (SceneManager.GetActiveScene().buildIndex + 1);

        if (y != 2) // Tymczasowo tylko dwa poziomy
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        }
        else
        {
            SceneManager.LoadScene(0);
        }
    }

    public static void Reset()
    {

            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);

    }
}