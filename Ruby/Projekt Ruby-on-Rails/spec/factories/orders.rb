FactoryBot.define do
  factory :order do
    owner_id { 1 }
    owner_type { 'MyString' }
    status { '' }
  end
end
