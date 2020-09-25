FactoryBot.define do
  factory :comment do
    content { Faker::Fallout.quote }
    association :product
  end
end
