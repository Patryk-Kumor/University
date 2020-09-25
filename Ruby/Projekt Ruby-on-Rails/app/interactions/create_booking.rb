class CreateBooking < ActiveInteraction::Base
  object :user, default: nil
  object :product

  def execute
    if @product.amount.positive?
      create_obj
      amount_update
      date_update
      owner_update
      name_update
    else
      errors.add(:product, 'not enough')
    end
  end

  def create_obj
    @booking = Booking.new(product: product)
    errors.merge!(@booking.errors) unless @booking.save
  end

  def date_update
    @booking.update start_date: Time.now, end_date: Time.now + 10.days
  end

  def owner_update
    @booking.user_name = !user ? 'gość' : user.email
    @booking.user_id = user.id if user
  end

  def name_update
    @booking.update product_name: product.name
  end

  def amount_update
    @product.update(amount: @product.amount - 1)
  end
end
