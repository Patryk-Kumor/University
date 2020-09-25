FactoryBot.define do
  factory :booking do
    user_id { 1 }
    product_id { 1 }
    start_date { '2018-11-19 19:42:45' }
    end_date { '2018-11-19 19:42:45' }
    returned { false }
  end
end
