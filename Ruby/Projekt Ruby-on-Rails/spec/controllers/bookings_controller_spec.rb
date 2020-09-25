require 'rails_helper'

RSpec.describe BookingsController, type: :controller do
  let(:product) { create :product }

  describe 'POST #create' do
    subject { post :create, params: { booking: { product_id: product.id } } }
    before do
      allow(CreateBooking).to receive(:run).and_return(outcome)
    end

    context 'when guest create booking' do
      let(:outcome) { instance_double(CreateBooking, valid?: true) }

      it do
        subject
        expect(controller.flash[:notice]).to eq('Rezerwacja została dodana')
      end

      it do
        expect(subject).to redirect_to(product_path(product.id))
      end

      context 'when guest can not create booking' do
        let(:outcome) { instance_double(CreateBooking, valid?: false, errors: errors) }
        let(:errors) { Struct.new(:full_messages).new('Nie można tego zrobić') }

        it do
          subject
          expect(controller.flash[:notice]).to eq('Nie można tego zrobić')
        end

        it do
          expect(subject).to redirect_to(product_path(product.id))
        end
      end
    end
  end

  describe 'GET #index' do
    subject { get :index }
    let(:admin) { create :admin_user }

    it do
      sign_in admin
      expect(subject.status).to eq(200)
    end
  end

  describe 'DELETE #destroy' do
    subject { delete :destroy, params: { id: booking.id } }
    let(:product) { create :product }
    let(:booking) { create :booking, product_id: product.id }
    let(:admin) { create :admin_user }

    it do
      sign_in admin
      expect(subject).to redirect_to(root_path)
    end

    it do
      sign_in admin
      subject
      expect(controller.flash[:notice]).to eq('Booking was destroyed!')
    end
  end

  describe 'PATCH #restore' do
    subject { patch :restore, params: { id: booking.id } }
    let(:product) { create :product }
    let(:booking) { create :booking, product_id: product.id }

    it do
      expect(subject).to redirect_to(bookings_path)
    end

    it do
      expect { subject }.to change { product.reload.amount }.by(1)
    end

    it do
      expect { subject }.to change { booking.reload.returned }.from(false).to(true)
    end
  end

  describe 'GET #user_bookings' do
    subject { patch :user_bookings }
    let(:user) { create :user }
    it do
      sign_in user
      expect(subject.status).to eq(200)
    end
  end
end
