using UnityEngine;
using System.Collections;

public class RandomRotator : MonoBehaviour
{
    [SerializeField]
  //  private 

    void Start()
    {
        float tumble = (Random.Range(0.25f, 0.5f));
        GetComponent<Rigidbody>().angularVelocity = Random.insideUnitSphere * tumble;
    }
}