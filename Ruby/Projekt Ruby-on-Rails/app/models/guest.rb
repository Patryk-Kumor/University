class Guest < ApplicationRecord
  has_many :orders, as: :owner

  def cart
    if orders.any?
      orders.first
    else
      Order.create owner: self
    end
  end
end
