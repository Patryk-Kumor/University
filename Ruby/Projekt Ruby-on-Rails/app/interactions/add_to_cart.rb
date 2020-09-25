class AddToCart < ActiveInteraction::Base
  object :guest
  object :product

  def execute
    guest.cart.order_items.create product: product
  end
end
