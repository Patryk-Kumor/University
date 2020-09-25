FactoryBot.define do
  factory :product do
    name { Faker::WorldOfWarcraft.hero << Faker::Number.number(2) }
    description { Faker::Fallout.quote }
    category { Faker::Fallout.character }
    amount { Faker::Number.number(2) }
    price { Faker::Number.decimal(2) }
  end
end
