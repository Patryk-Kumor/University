using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ammo : MonoBehaviour
{


    public LifeLevels LifeLevel;

    public int Ammount = 10;

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.name=="Cat")
        {
            LifeLevel.EnergyChange(1);
            Weapon weapon = other.GetComponent<Weapon>() as Weapon;
            weapon.AddBullets(Ammount);
            Destroy(gameObject);
        }
    }
}
