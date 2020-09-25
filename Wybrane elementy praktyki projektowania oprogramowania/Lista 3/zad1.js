// ZADANIE 1
var Car = 
{
    brand: undefined,
    'color': undefined,
    giveSound: function() 
    {
      console.log("wrr");
    },
    get getBrand() 
    {
      return this.brand;
    },
    set setBrand(brand) 
    {
      this.brand = brand;
    }
}
console.log(Car.brand);
Car.brand = "Ferrari";
console.log(Car.brand);
Car.brand = "Porsche";
console.log(Car.brand, "\n");
//Car.setBrand("Porsche"); is not a function
//console.log(Car.getBrand()); is not a function
console.log( Car.color);
Car.color="red";
console.log(Car.color, "\n");

Car.giveSound();

// Nowa metoda
Car.giveOtherSound = function () 
{
  console.log("wrrrum");
};
Car.giveOtherSound();

// Nowe pole
Car.productionDate = "1964";
console.log(Car.productionDate, "\n");

// Nowe pole z właściwościami
//var model = null
Object.defineProperty(Car, 'model', 
{
  get: function () 
  {
    return model
  },
  set: function (model)
  {
    model = model
  }
});
console.log(Car.model);
var model = "911"
console.log(Car.model, "\n");

//
const cat = {};
cat.race = "Sphynx";
console.log(cat.race);
Object.defineProperty(cat, 'race', 
{
  value: "Maine Coon",
  writable: false
});
cat.race = "Sphynx"; // i tak nie nadpisze
console.log(cat.race);
/*
Object.defineProperty(cat, 'race', 
{
  value: "Bengal",
  writable: false
});
*/
console.log(cat.race);


var cats = {};
function meow()
{
  console.log("meow");
}
Object.defineProperty(cats, 'giveSound', 
{
  value: meow,
});
cats.giveSound();