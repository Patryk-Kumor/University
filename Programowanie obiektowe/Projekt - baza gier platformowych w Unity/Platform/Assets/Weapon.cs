using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Weapon : MonoBehaviour
{

    public GameObject Bullet;

    public Transform BulletSpawnPoint;

    public int MagazineCapacity = 10;

    public int StartAmmo = 30;

    private int CurrentAmmoAmount;

    private int CurrentMagazineAmount;


    void Start()
    {
        CurrentMagazineAmount = MagazineCapacity;
        CurrentAmmoAmount = StartAmmo;
    }

    void Update()
    {
        if (Input.GetButtonDown("Reload"))
        {
            int bulletsToAdd = MagazineCapacity - CurrentMagazineAmount;

            if (CurrentAmmoAmount < bulletsToAdd)
            {
                bulletsToAdd = CurrentAmmoAmount;
            }

            CurrentAmmoAmount -= bulletsToAdd;
            CurrentMagazineAmount += bulletsToAdd;
        }

        if (Input.GetButtonDown("Fire1") && CurrentMagazineAmount > 0)
        {
            Instantiate(Bullet, BulletSpawnPoint.position, BulletSpawnPoint.rotation);
            CurrentMagazineAmount--;
        }
    }

    public void AddBullets(int amount)
    {
        CurrentAmmoAmount = CurrentAmmoAmount + 10;
    }
}
