using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BallMovement : MonoBehaviour
{
    public float ballInitialVelocity = 10f;

    private Rigidbody rb;

    private bool IsActive;

    private int Points = 0;

    public int MaxBlocks = 1;

    public Text PointsText;

    public Text WinOrLostText;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        WinOrLostText.text = "Ready? Press 'Ctrl'";
    }

    void FixedUpdate()
    {
        rb.velocity = 20 * (rb.velocity.normalized);

        if (Input.GetButtonDown("Fire1") && IsActive == false)
        {
            transform.parent = null;

            IsActive = true;

            rb.AddForce(new Vector3(ballInitialVelocity, ballInitialVelocity, 0));

            WinOrLostText.text = "";
        }
    }

    public void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Ground")
        {
            WinOrLostText.text = "You have lost! ";
            Destroy(gameObject);
        }
        if (collision.gameObject.tag == "Block")
        {
            if (Points < MaxBlocks)
            {
                Points += 1;
                SetText();
            }
            if (Points == MaxBlocks)
            {
                WinOrLostText.text = "You have won!";
                Destroy(gameObject);
            }
        }
    }

    void SetText()
    {
        PointsText.text = "Points: " + Points.ToString();
    }
}
