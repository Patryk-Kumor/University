require 'rails_helper'

RSpec.describe Product do
  let(:product) { create :product }

  describe '#display_price' do
    it do
      expect(product.display_price).to eq(product.price)
    end
  end

  describe '#display_in_pln' do
    it do
      puts "\n" + product.display_in_pln + "\n"
      expect(product.display_in_pln[-4..-1]).to eq(' PLN')
    end
  end

  context 'when there is free item' do
    let(:product) { create :product, price: 0 }

    it { expect(product.display_price).to eq(nil) }
  end
end
