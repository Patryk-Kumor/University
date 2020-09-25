using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    float x;
    float y;
    float dx;
    float dy;

    private TextMesh text;

    public int score;

    public PlayerMovement Cat;

    public Renderer ren;

    void Start()
    {
        Renderer ren = GetComponent<Renderer>();
        text = GetComponent<TextMesh>();
        Cat = FindObjectOfType<PlayerMovement>();
        score = 0;

        dx = transform.position.x - Camera.main.gameObject.transform.position.x;
        dy = transform.position.y - Camera.main.gameObject.transform.position.y;
    }

    void Update()
    {
        x = Camera.main.gameObject.transform.position.x + dx;
        y = Camera.main.gameObject.transform.position.y + dy;
        transform.position = new Vector3(x, y, transform.position.z);
    }

    public void ChangeScore(int value)
    {
        score += value;
        string displayText = "Score: "+ score.ToString();

        text = GetComponent<TextMesh>();

        text.text = displayText;
    }


}

