class CartsController < ApplicationController
  before_action :authenticate_user!, only: %i[finalize]

  def index
    add_breadcrumb 'Cart', :carts_path
    @cart = current_guest.cart
    @value = @cart.cart_sum_check
  end

  def finalize
    s = current_guest.cart.cart_check
    current_guest.cart.order_items.each do |item|
      CreateBooking.run(user: current_user, product: item.product)
      item.destroy
    end
    flash[:notice] = s
    redirect_to '/products'
  end
end
