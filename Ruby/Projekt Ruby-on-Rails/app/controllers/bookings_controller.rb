class BookingsController < ApplicationController
  before_action :authenticate_admin_user!, only: %i[index destroy]
  before_action :authenticate_user!, only: %i[user_bookings]

  def create
    product = Product.find(params[:booking][:product_id])
    outcome = CreateBooking.run(user: current_user, product: product)
    flash[:notice] = if outcome.valid?
                       'Rezerwacja została dodana'
                     else
                       'Nie można tego zrobić'
                     end
    redirect_to product
  end

  def index
    add_breadcrumb 'Bookings', :bookings_path
    @bookings = Booking.all
  end

  def destroy
    @booking = Booking.find(params[:id])
    @booking.destroy
    redirect_back(fallback_location: root_path)
    flash[:notice] = 'Booking was destroyed!'
  end

  def restore
    @booking = Booking.find(params[:id])
    @product = Product.find(@booking.product_id)
    @product.update amount: @product.amount + 1
    @booking.update returned: true
    redirect_to bookings_path
  end

  def user_bookings
    add_breadcrumb 'Bookings', :bookings_user_bookings_path
    @current_name = current_user.email
    @bookings = current_user.bookings
  end
end
