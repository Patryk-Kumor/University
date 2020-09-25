using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PlayerMovement : MonoBehaviour
{
    public float Speed = 50;

    private Vector3 Position;

    private Rigidbody rb;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void FixedUpdate()
    {
        float X = transform.position.x + (Input.GetAxis("Horizontal") * Speed);

        Position = new Vector3(Mathf.Clamp(X, -9, 9), -3.5819f, 0);

        transform.SetPositionAndRotation(Position, Quaternion.identity);
        //transform.position = Position;

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
        rb.velocity = (new Vector3(0, 0, 0));
    }

    public void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Ball")
        {
            rb.velocity = (new Vector3(0, 0, 0));
            print("spotkanie");
        }
    }
}
