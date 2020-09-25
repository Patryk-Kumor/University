require 'rails_helper'

RSpec.describe Booking do
  let(:product) { create :product }
  context 'when booking is created' do
    let(:booking) { product.bookings.create! }

    it 'always relates to the same product' do
      expect(product).to eq(booking.product)
    end

    it 'has returned field set to false' do
      expect(booking.returned).to be_falsey
    end
  end

  describe '#display_status' do
    let(:booking) { product.bookings.create(returned: true) }
    it do
      expect(booking.display_status).to be true
    end
  end
end
